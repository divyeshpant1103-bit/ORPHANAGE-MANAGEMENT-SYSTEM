# Security, Testing, and Deployment Checklists

## A) Security before running
- [ ] All secrets moved to `.env` and not hardcoded
- [ ] `.env` excluded from git and `.env.example` present
- [ ] Passwords hashed with modern algorithm
- [ ] Participant/admin role checks enforced on backend routes
- [ ] Server-side validation for every registration field
- [ ] Input sanitization enabled for user-supplied strings
- [ ] No raw SQL concatenation; parameterized queries only
- [ ] Public endpoints protected by rate limiting
- [ ] CAPTCHA enforced for registration submissions
- [ ] CORS restricted to known frontend domains

## B) Local run and test checklist
- [ ] App starts without runtime errors
- [ ] Registration happy path works end-to-end
- [ ] Invalid input returns validation errors
- [ ] Duplicate email/phone/team blocked
- [ ] Participant cannot access admin routes
- [ ] Admin can approve/reject registrations
- [ ] Notification events are triggered correctly
- [ ] Lint passes
- [ ] Unit and integration tests pass
- [ ] Dependency vulnerability scan run and reviewed

## C) Pre-deploy hardening checklist
- [ ] HTTPS enforced
- [ ] Secure response headers enabled
- [ ] Error messages avoid sensitive internals
- [ ] Request/response logs avoid sensitive fields
- [ ] Backup strategy configured for primary database
- [ ] Monitoring and alerts configured
- [ ] Health check endpoint verified

## D) Deploy safely checklist
- [ ] Deploy to staging first
- [ ] Validate staging auth, registration, admin review, notifications
- [ ] Run smoke tests after staging deploy
- [ ] Deploy to production only after staging sign-off
- [ ] Keep previous release/version for rollback

## E) Post-launch checklist
- [ ] Admin access verified
- [ ] Export data feature verified
- [ ] Notification delivery verified
- [ ] Abuse/spam behavior monitored
- [ ] Incident response contact path documented
- [ ] Rollback runbook stored and shared
